package ubb.scs.map.repository.file;

import ubb.scs.map.domain.Entity;
import ubb.scs.map.domain.Friendship;
import ubb.scs.map.domain.Tuple;
import ubb.scs.map.domain.User;
import ubb.scs.map.domain.validators.ValidationException;
import ubb.scs.map.domain.validators.Validator;
import ubb.scs.map.repository.FriendshipRepoInterface;
import ubb.scs.map.utils.MultiMap;


import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.LocalTime;
import java.util.Collection;
import java.util.List;

public class FriendshipRepo extends AbstractFileRepository<Tuple<Long,Long>,Friendship> implements FriendshipRepoInterface {

    private MultiMap<Long,Long> friends = new MultiMap<>();

    public FriendshipRepo(Validator<Friendship> validator, String fileName) {
        super(validator, fileName);
        createFriendsList();
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
    public Friendship createEntity(String line) {
        if("".equals(line))
            throw new ValidationException("Check for empty lines in input file!");
        String[] splitted = line.split(";");
        Friendship fr = new Friendship();

        fr.setId(new Tuple<>(Long.parseLong(splitted[0]),Long.parseLong(splitted[1])));

        String[] date = splitted[2].split(":");

        LocalDate localDate = LocalDate.of(Integer.parseInt(date[0]),
                Integer.parseInt(date[1]),Integer.parseInt(date[2]));

        fr.setDate(localDate);
        return fr;
    }

    @Override
    public String saveEntity(Friendship entity) {
        String toSave = "";
        toSave+=String.valueOf(entity.getId().getE1())+";"+
                String.valueOf(entity.getId().getE2())+";"+
                String.valueOf(entity.getDate().getYear())+":"+
                String.valueOf(entity.getDate().getMonthValue())+":"+
                String.valueOf(entity.getDate().getDayOfMonth());

        return toSave;
    }
}
