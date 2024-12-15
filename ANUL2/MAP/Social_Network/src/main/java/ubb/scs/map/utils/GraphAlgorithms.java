package ubb.scs.map.utils;

import ubb.scs.map.domain.User;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashSet;
import java.util.List;

public class GraphAlgorithms {
    private static void dfs(Long currentUserID, HashSet<Long> visited,MultiMap<Long,Long> friendsList,List<Long> members){
        members.add(currentUserID);
        visited.add(currentUserID);
        Collection<Long> friendsOfCurrent = friendsList.get(currentUserID);
        if(friendsOfCurrent!=null)
            for(Long friendID : friendsList.get(currentUserID))
                if(!visited.contains(friendID))
                    dfs(friendID,visited,friendsList,members);
    }

    public static ArrayList<Long> determineComunities(Long startUserID, HashSet<Long> visited,MultiMap<Long,Long> friendsList){
        ArrayList<Long> members = new ArrayList<>();

        dfs(startUserID,visited,friendsList,members);

        return members;
    }
}
