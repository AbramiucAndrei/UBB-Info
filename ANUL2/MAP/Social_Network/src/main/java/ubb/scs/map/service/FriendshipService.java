package ubb.scs.map.service;

import ubb.scs.map.domain.Friendship;
import ubb.scs.map.domain.Tuple;
import ubb.scs.map.domain.User;
import ubb.scs.map.repository.FriendshipRepoInterface;
import ubb.scs.map.repository.Repository;
import ubb.scs.map.repository.file.FriendshipRepo;
import ubb.scs.map.utils.GraphAlgorithms;
import ubb.scs.map.utils.MultiMap;
import ubb.scs.map.utils.TupleHelper;
import ubb.scs.map.utils.TupleManip;

import java.util.Collection;
import java.util.HashSet;
import java.util.Optional;

public class FriendshipService implements ServiceInterface<Tuple<Long,Long>, Friendship>,FriendshipServiceInt{
    private FriendshipRepoInterface friendshipRepo;

    public FriendshipService(FriendshipRepoInterface fr){
        friendshipRepo =fr;

    }
    @Override
    public Friendship findOne(Tuple<Long,Long> usersTuple) {
        return friendshipRepo.findOne(usersTuple).orElse(null);
    }

    @Override
    public Iterable<Friendship> findAll() {
        return friendshipRepo.findAll();
    }

    public Iterable<Tuple<Long,Long>> getKeys(){
        return friendshipRepo.findAllKeys();
    }

    @Override
    public Friendship delete(Tuple<Long, Long> usersTuple) {
        Optional<Friendship> fr = friendshipRepo.delete(usersTuple);
        if(fr.isPresent()){
            return fr.get();
        }
        else{
            TupleManip inversor = TupleHelper::inverser;
            Tuple<Long,Long> inversed_friendship_id = inversor.calculate(usersTuple);
            return friendshipRepo.delete(inversed_friendship_id).orElse(null);
        }
    }

    @Override
    public Friendship save(User u1, User u2) {
        Tuple<Long,Long> ids_tuple = new Tuple<>(u1.getId(),u2.getId());
        Friendship friendship = new Friendship();
        friendship.setId(ids_tuple);

        TupleManip inversor = TupleHelper::inverser;
        Tuple<Long,Long> inversed_friendship_id = inversor.calculate(ids_tuple);

        Optional<Friendship> inverse_exists = friendshipRepo.findOne(inversed_friendship_id);
        return inverse_exists.orElseGet(
                () -> friendshipRepo.save(friendship).orElse(null)
        );

    }

    public int calculateNumberOfComunities(Iterable<User> allUsers){

        HashSet<Long> visited = new HashSet<>();
        int comunities=0;
        for(User u : allUsers)
            if(!visited.contains(u.getId())){
                GraphAlgorithms.determineComunities(u.getId(),visited, friendshipRepo.getAllFriendshipsLists());
                comunities++;
            }
        return comunities;
    }

    public MultiMap<Integer,Long> allComunities(Iterable<User> allUsers){
        HashSet<Long> visited = new HashSet<>();
        MultiMap<Integer,Long> comunity = new MultiMap<>();

        int comunities=0;
        for(User u : allUsers)
            if(!visited.contains(u.getId())){
                comunities++;
                comunity.putCollection(comunities,
                        GraphAlgorithms.determineComunities(u.getId(),visited, friendshipRepo.getAllFriendshipsLists()));
            }
        return comunity;
    }

    public Collection<Long> mostSociableComunity(MultiMap<Integer,Long> comunities){
        Collection<Long> mostSociable = null;
        for(Collection<Long> eachComunity : comunities.values()){
            if(mostSociable==null || eachComunity.size()>mostSociable.size())
                mostSociable=eachComunity;
        }

        return mostSociable;
    }
}
