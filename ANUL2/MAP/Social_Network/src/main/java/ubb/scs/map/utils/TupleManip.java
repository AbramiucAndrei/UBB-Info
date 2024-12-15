package ubb.scs.map.utils;

import ubb.scs.map.domain.Tuple;

@FunctionalInterface
public interface TupleManip {
    public Tuple<Long,Long> calculate(Tuple<Long,Long> given);
}
