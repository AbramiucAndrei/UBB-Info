package ubb.scs.map.repository.database;

import ubb.scs.map.domain.User;
import ubb.scs.map.domain.validators.Validator;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class UserDBRepository extends AbstractDBRepository<Long, User> {

    public UserDBRepository(String dbName,String tableName, String user, String pass, Validator<User> validator) {
        super(dbName,tableName, user, pass, validator);
    }

    @Override
    protected User createEntity(ResultSet line) {
        User newUser = null;
        try {
            newUser= new User(line.getString("first_name"),
                                    line.getString("last_name"));
            newUser.setId(Long.valueOf(line.getString("uid")));

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return newUser;
    }

    @Override
    public Optional<User> save(User entity) {
        String saveQuery = String.format("INSERT INTO users(uid,first_name,last_name) VALUES(%d,'%s','%s')",entity.getId(),entity.getFirstName(),entity.getLastName());
        String verifyQuery = String.format("SELECT * FROM users WHERE uid = %d",entity.getId());

        super.setVerifyQuery(verifyQuery);
        super.setSaveQuery(saveQuery);

        return super.save(entity);
    }

    @Override
    public Optional<User> delete(Long id){
        String deleteQuery = String.format("DELETE FROM users WHERE uid = %d",id);
        super.setDeleteQuery(deleteQuery);

        String verifyQuery = String.format("SELECT * FROM users WHERE uid = %d",id);
        super.setVerifyQuery(verifyQuery);

        return super.delete(id);
    }

    @Override
    public Optional<User> update(User entity){
        String query = String.format("UPDATE users SET first_name = '%s', last_name = '%s' WHERE uid = %d",
                entity.getFirstName(),entity.getLastName(),entity.getId());
        super.setUpdateQuery(query);

        return super.update(entity);
    }

    @Override
    public Iterable<Long> findAllKeys() {
        String query = "SELECT uid FROM users";
        List<Long> ids = new ArrayList<>();

        try (Statement statement = connectionToDb.createStatement();
             ResultSet idSet = statement.executeQuery(query)) {

            while (idSet.next()) {
                ids.add(idSet.getLong("uid")); // Retrieve the "uid" column value
            }
        } catch (Exception e) {
            e.printStackTrace(); // Handle exceptions appropriately
        }
        return ids;
    }

    @Override
    public Optional<User> findOne(Long id){
        String query = String.format("SELECT * FROM users WHERE uid = %d",id);
        super.setVerifyQuery(query);

        return super.findOne(id);
    }

}
