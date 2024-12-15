package ubb.scs.map.domain.validators;


import ubb.scs.map.domain.User;

public class UserValidator implements Validator<User> {
    @Override
    public void validate(User entity) throws ValidationException {
        //TODO: implement method validate
        if(entity.getFirstName().equals("") || entity.getLastName().equals(""))
            throw new ValidationException("User is not valid!");
    }
}
