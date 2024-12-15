package ubb.scs.map.service;

import ubb.scs.map.domain.Entity;
import ubb.scs.map.domain.Friendship;
import ubb.scs.map.domain.User;
import ubb.scs.map.repository.Repository;

import static java.lang.Math.max;

public interface ServiceInterface <ID,E extends Entity<ID>>{

    E findOne(ID id);

    Iterable<E> findAll();

    E delete(ID id);


//    public User updateUser(Long id,String firstName,String lastName){
//        User updatedUser = new User(firstName,lastName);
//        updatedUser.setId(id);
//        return userRepo.update(updatedUser);
//    }
}
