package ubb.scs.map.repository;

import ubb.scs.map.domain.Friendship;
import ubb.scs.map.domain.Tuple;
import ubb.scs.map.utils.MultiMap;

import java.util.Collection;

public interface FriendshipRepoInterface extends Repository<Tuple<Long,Long>,Friendship>{
    public Collection<Long> getAllFriendsOfUserWithId(Long id);

    public MultiMap<Long,Long> getAllFriendshipsLists();
}
