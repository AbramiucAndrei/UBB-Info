package ubb.scs.map.repository.file;

import ubb.scs.map.domain.User;
import ubb.scs.map.domain.validators.ValidationException;
import ubb.scs.map.domain.validators.Validator;

public class UserRepository extends AbstractFileRepository<Long, User>{
    public UserRepository(Validator<User> validator, String fileName) {
        super(validator, fileName);
    }

    @Override
    public User createEntity(String line) {
        if("".equals(line))
            throw new ValidationException("Check for empty lines in input file!");
        String[] splited = line.split(";");
        User u = new User(splited[1], splited[2]);
        u.setId(Long.parseLong(splited[0]));
        return u;
    }

    @Override
    public String saveEntity(User entity) {
        String s = entity.getId() + ";" + entity.getFirstName() + ";" + entity.getLastName();
        return s;
    }


}
