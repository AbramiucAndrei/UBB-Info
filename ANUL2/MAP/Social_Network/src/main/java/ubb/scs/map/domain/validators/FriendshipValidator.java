package ubb.scs.map.domain.validators;

import ubb.scs.map.domain.Entity;
import ubb.scs.map.domain.Friendship;

public class FriendshipValidator implements Validator<Friendship> {
    @Override
    public void validate(Friendship entity) throws ValidationException {
        if(entity.getDate().getYear()<1970 || entity.getId().getE1()== entity.getId().getE2())
            throw new ValidationException("Friendship not valid");
    }
}
