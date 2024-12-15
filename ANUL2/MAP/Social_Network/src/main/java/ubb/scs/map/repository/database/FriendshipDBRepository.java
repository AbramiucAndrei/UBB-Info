package ubb.scs.map.repository.database;

import ubb.scs.map.domain.Friendship;
import ubb.scs.map.domain.Tuple;
import ubb.scs.map.domain.User;
import ubb.scs.map.domain.validators.Validator;
import ubb.scs.map.repository.FriendshipRepoInterface;
import ubb.scs.map.utils.MultiMap;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import java.util.Optional;

public class FriendshipDBRepository extends AbstractDBRepository<Tuple<Long,Long>, Friendship> implements FriendshipRepoInterface {
    private MultiMap<Long,Long> friends = new MultiMap<>();

    public FriendshipDBRepository(String dbName, String tableName, String user, String pass, Validator<Friendship> validator) {
        super(dbName, tableName, user, pass, validator);
        createFriendsList();
    }

    @Override
    protected Friendship createEntity(ResultSet line) {
        Friendship newFriendship = null;
        try{
            newFriendship = new Friendship();

            Tuple<Long,Long> friendshipTuple = new Tuple<>(
                    Long.parseLong(line.getString("uid1")),
                    Long.parseLong(line.getString("uid2"))
            );
            newFriendship.setId(friendshipTuple);

            String[] date = line.getString("fr_date")
                            .split("-");
            LocalDate localDate = LocalDate.of(Integer.parseInt(date[0]),
                                                Integer.parseInt(date[1]),
                                                 Integer.parseInt(date[2]));
            newFriendship.setDate(localDate);

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return newFriendship;
    }

    @Override
    public Optional<Friendship> save(Friendship entity){
        String date = entity.getDate().toString();

        String saveQuery = String.format("INSERT INTO friendships(uid1,uid2,fr_date) VALUES(%d,%d,'%s')",
                entity.getId().getE1(),entity.getId().getE2(),date);

        String verifyQuery = String.format("SELECT FROM friendships WHERE uid1 = %d AND uid2 = %d",entity.getId().getE1(),entity.getId().getE2());

        super.setVerifyQuery(verifyQuery);
        super.setSaveQuery(saveQuery);

        return super.save(entity);
    }

    @Override
    public Optional<Friendship> delete(Tuple<Long,Long> id){
        String query = String.format("DELETE FROM friendships WHERE uid1=%d AND uid2=%d",
                id.getE1(),id.getE2());
        super.setDeleteQuery(query);

        String verifyQuery = String.format("SELECT * FROM friendships WHERE uid1 = %d AND uid2 = %d",
                id.getE1(),id.getE2());
        super.setVerifyQuery(verifyQuery);

        return super.delete(id);
    }

    @Override
    public Optional<Friendship> update(Friendship entity){
        String query = String.format("UPDATE friendships SET fr_date = %s WHERE uid1 = %d AND uid2 = %d",
                entity.getDate(),entity.getId().getE1(),entity.getId().getE2());
        super.setUpdateQuery(query);

        return super.update(entity);
    }

    private void createFriendsList(){
        for(Friendship fr : findAll()){
            Long id1,id2;
            id1= fr.getId().getE1();
            id2= fr.getId().getE2();

            friends.putIfAbsent(id1,id2);
            friends.putIfAbsent(id2,id1);
        }
    }

    @Override
    public Collection<Long> getAllFriendsOfUserWithId(Long id){
        return friends.get(id);
    }

    @Override
    public MultiMap<Long,Long> getAllFriendshipsLists(){
        return friends;
    }

    @Override
    public Iterable<Tuple<Long, Long>> findAllKeys() {
        String query = "SELECT uid1, uid2 FROM friendships";
        List<Tuple<Long, Long>> ids = new ArrayList<>();

        try (Statement statement = connectionToDb.createStatement();
             ResultSet idSet = statement.executeQuery(query)) {

            while (idSet.next()) {
                Long uid1 = idSet.getLong("uid1");
                Long uid2 = idSet.getLong("uid2");
                ids.add(new Tuple<>(uid1, uid2)); // Create a tuple and add to the list
            }
        } catch (Exception e) {
            e.printStackTrace(); // Handle exceptions appropriately
        }
        return ids;
    }

    @Override
    public Optional<Friendship> findOne(Tuple<Long,Long> id){
        String query = String.format("SELECT * FROM friendships WHERE uid1 = %d and uid2 = %d",id.getE1(),id.getE2());
        super.setVerifyQuery(query);

        return super.findOne(id);
    }
}
