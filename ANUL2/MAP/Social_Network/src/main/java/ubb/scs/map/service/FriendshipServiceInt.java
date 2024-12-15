package ubb.scs.map.service;

import ubb.scs.map.domain.Friendship;
import ubb.scs.map.domain.User;

public interface FriendshipServiceInt {
    Friendship save(User u1, User u2);
}
