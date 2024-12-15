package ubb.scs.map.service;

import ubb.scs.map.domain.User;
import ubb.scs.map.repository.Repository;

import static java.lang.Math.max;

public class UserService implements ServiceInterface<Long,User>,UserServiceInt{
    private final Repository<Long, User> userRepo;

    public UserService(Repository<Long,User> userRepo){
        this.userRepo=userRepo;
    }

    @Override
    public User findOne(Long id){
        return userRepo.findOne(id).orElse(null);
    }

    @Override
    public Iterable<User> findAll(){
        return userRepo.findAll();
    }

    @Override
    public User save(String firstName,String lastName){
        User newUser = new User(firstName,lastName);
        long maxid= 0;
        for(User u : userRepo.findAll())
            maxid=max(maxid,u.getId());

        newUser.setId(maxid+1);
        return userRepo.save(newUser).orElse(null);
    }

    @Override
    public User delete(Long id){
        return userRepo.delete(id).orElse(null);
    }

    @Override
    public User updateUser(Long id,String firstName,String lastName){
        User updatedUser = new User(firstName,lastName);
        updatedUser.setId(id);
        return userRepo.update(updatedUser).orElse(null);
    }

}
