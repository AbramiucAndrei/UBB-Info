package ubb.scs.map.domain;

import java.time.LocalDate;
import java.util.Objects;

public class Friendship extends Entity<Tuple<Long, Long>> {
    private LocalDate date = LocalDate.now();

    public LocalDate getDate() {
        return date;
    }

    public void setDate(LocalDate newDate){
        date=newDate;
    }

    @Override
    public String toString() {
        return "Friendship{" +
                "ID1: " + getId().getE1().toString()+
                "; ID2: " + getId().getE2().toString()+
                "; Date:" + date +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Friendship that = (Friendship) o;
        return this.getId().equals(that.getId());
    }

    @Override
    public int hashCode() {
        return Objects.hashCode(getId());
    }
}