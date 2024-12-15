package ubb.scs.map.repository.database;

import ubb.scs.map.domain.Entity;
import ubb.scs.map.domain.validators.Validator;
import ubb.scs.map.repository.Repository;
import ubb.scs.map.repository.memory.InMemoryRepository;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public abstract class AbstractDBRepository<ID, E extends Entity<ID>> implements Repository<ID,E> {

    String databaseName;
    String tableName;

    String user;
    String password;

    Connection connectionToDb;

    private String saveQuery;
    private String deleteQuery;
    private String updateQuery;
    private String verifyQuery;

    private Validator<E> validator;

    public AbstractDBRepository(String dbName,String tableName, String user, String pass, Validator<E> validator) {
        this.validator=validator;

        this.databaseName=dbName;
        this.tableName=tableName;
        this.user=user;
        this.password=pass;

        this.connectionToDb = initiateConnection();
    }

    protected abstract E createEntity(ResultSet line);

    private Connection initiateConnection(){
        Connection conn = null;
        try {
            //Class.forName("org.postgres.Driver");
            conn = DriverManager.getConnection("jdbc:postgresql://localhost:5432/"+databaseName,user,password);

            if(conn!=null)
                System.out.println("Connection Established");
            else
                System.out.println("Connection failed");

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return conn;
    }

    @Override
    public Iterable<E> findAll(){

        List<E> all= new ArrayList<>();
        Statement statement;
        ResultSet line=null;
        try {
            String query = String.format("SELECT * FROM %s",tableName);
            statement = connectionToDb.createStatement();
            line = statement.executeQuery(query);

            while(line.next()){
                E entity = createEntity(line);
                all.add(entity);
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return all;
    }



    @Override
    public Optional<E> save(E entity) {
        if (entity == null) {
            throw new IllegalArgumentException("id must not be null");
        }
        validator.validate(entity);

        Optional<E> e = findOne(entity.getId());

        if(e.isEmpty()){
            //haven't found one entity with this id
            try(Statement statement = connectionToDb.createStatement()) {

                statement.executeUpdate(saveQuery);

            } catch (SQLException ex) {
                throw new RuntimeException(ex);
            }
        }

        return e;
    }


    @Override
    public Optional<E> findOne(ID id){

        //////////////////////////
        Optional<E> entity = Optional.empty();

        try (Statement statement = connectionToDb.createStatement();
             ResultSet verifyExistance = statement.executeQuery(verifyQuery)) {

            if (verifyExistance.next()) {
                // Move the cursor to the first row and create the entity
                entity = Optional.of(createEntity(verifyExistance));
            }
            // If `next()` returns false, it means no rows were found, and the entity remains empty.
        } catch (SQLException ex) {
            throw new RuntimeException("Error accessing the database: " + ex.getMessage(), ex);
        }

        return entity;
    }

    @Override
    public Optional<E> delete(ID id) {
        if (id == null) {
            throw new IllegalArgumentException("id must not be null");
        }

        Optional<E> search = findOne(id);
        if(search.isPresent()){
            try {

                Statement statement = connectionToDb.createStatement();
                statement.executeUpdate(deleteQuery);

            } catch (SQLException e) {
                throw new RuntimeException(e);
            }
        }
        return search;
    }

    @Override
    public Optional<E> update(E entity) {
        if(entity==null){
            throw new IllegalArgumentException("ENTITY CANNOT BE NULL");
        }
        validator.validate(entity);

        Optional<E> entity2 = findOne(entity.getId());

        if (entity2.isPresent())
        {
            Statement statement = null;
            try {
                statement = connectionToDb.createStatement();
                statement.executeUpdate(updateQuery);
                entity2 = Optional.empty();
            } catch (SQLException ex) {
                throw new RuntimeException(ex);
            }
        }else{
            entity2 = Optional.of(entity);
        }

        return entity2;
    }

    public void setSaveQuery(String saveQuery) {
        this.saveQuery = saveQuery;
    }

    public void setDeleteQuery(String deleteQuery) {
        this.deleteQuery = deleteQuery;
    }

    public void setUpdateQuery(String updateQuery) {
        this.updateQuery = updateQuery;
    }

    public void setVerifyQuery(String verifyQuery) {
        this.verifyQuery = verifyQuery;
    }
}
