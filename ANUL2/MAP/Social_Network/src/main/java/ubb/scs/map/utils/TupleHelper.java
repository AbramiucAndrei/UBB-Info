package ubb.scs.map.utils;

import ubb.scs.map.domain.Tuple;

public class TupleHelper {
    public static Tuple<Long,Long> inverser(Tuple<Long, Long> given_tuple){
        Tuple<Long,Long> inversed = new Tuple<>(given_tuple.getE2(), given_tuple.getE1());
        return inversed;
    }

    public Tuple<Long,Long> duplicator(Tuple<Long,Long> given_tuple){
        Tuple<Long,Long> duplicated = new Tuple<>(given_tuple.getE1(), given_tuple.getE2());
        return duplicated;
    }
}
