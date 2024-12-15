package ubb.scs.map.service;

import ubb.scs.map.domain.User;

public interface UserServiceInt {
    User updateUser(Long id, String firstName, String lastName);
    User save(String firstName,String secondName);
}
