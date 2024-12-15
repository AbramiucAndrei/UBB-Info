package ubb.scs.map;

import ubb.scs.map.UI.Console;
import ubb.scs.map.domain.Friendship;
import ubb.scs.map.domain.Tuple;
import ubb.scs.map.domain.User;
import ubb.scs.map.domain.validators.FriendshipValidator;
import ubb.scs.map.domain.validators.UserValidator;
import ubb.scs.map.domain.validators.Validator;
import ubb.scs.map.repository.Repository;
import ubb.scs.map.repository.database.FriendshipDBRepository;
import ubb.scs.map.repository.database.UserDBRepository;
import ubb.scs.map.repository.file.FriendshipRepo;
import ubb.scs.map.repository.file.UserRepository;
import ubb.scs.map.service.FriendshipService;
import ubb.scs.map.service.UserService;

import java.util.Objects;

// Press Shift twice to open the Search Everywhere dialog and type `show whitespaces`,
// then press Enter. You can now see whitespace characters in your code.
public class Main {
    public static void main(String[] args) {

//        Repository<Long, User> repo = new InMemoryRepository<Long, User>(new UserValidator());
//        Repository<Long, User> repoFile = new UtilizatorRepository(new UserValidator(), "./data/utilizatori.txt");
//        User u1 = new User("AlexiaUpdatata", "c");
//        User u2 = new User("MariusUpdatat", "g");
//        User u3 = new User("mihai", "h");
//        u1.setId(3L);
//        u2.setId(7L);
//        u3.setId(8L);
//        Friendship f = new Friendship();
//        f.setId(new Tuple<User, User>(u1, u2));
//        Friendship f2 = new Friendship();
//        f2.setId(new Tuple<User, User>(u2, u1));
//        System.out.println(new Tuple<User, User>(u1, u2).equals(new Tuple<User, User>(u2, u1)));
//        System.out.println(f.equals(f2));
//        try {
//            repoFile.save(u1);
//            repoFile.save(u2);
//            repoFile.save(u3);
//        }catch(IllegalArgumentException e)
//        {
//            System.out.println(e.getMessage());
//        }catch(ValidationException e)
//        {
//            System.out.println(e.getMessage());
//        }
//        try{
//            User u;
//            u=repoFile.update(u1);
//            if(u==null){
//                System.out.println("Utilizatorul a fost updatat");
//            }
//            else{
//                System.out.println("Utilizatorul nu a fost updatat");
//            }
//            u=repoFile.update(u2);
//            if(u==null){
//                System.out.println("Utilizatorul a fost updatat");
//            }
//            else{
//                System.out.println("Utilizatorul nu a fost updatat");
//            }
//            u=repoFile.update(u3);
//            if(u==null){
//                System.out.println("Utilizatorul a fost updatat");
//            }
//            else{
//                System.out.println("Utilizatorul nu a fost updatat");
//            }
//        }
//        catch(IllegalArgumentException e){
//            System.out.println(e.getMessage());
//        }
//        catch(ValidationException e){
//            System.out.println(e.getMessage());
//        }
//        try{
//            User u;
//            u=repoFile.delete(u1.getId());
//            if(u!=null){
//                System.out.println("Utilizatorul a fost sters");
//            }
//            else{
//                System.out.println("Utilizatorul nu a fost sters");
//            }
//            u=repoFile.delete(u2.getId());
//            if(u!=null){
//                System.out.println("Utilizatorul a fost sters");
//            }
//            else{
//                System.out.println("Utilizatorul nu a fost sters");
//            }
//            u=repoFile.delete(u3.getId());
//            if(u!=null){
//                System.out.println("Utilizatorul a fost sters");
//            }
//            else{
//                System.out.println("Utilizatorul nu a fost sters");
//            }
//        }
//        catch(IllegalArgumentException e){
//            System.out.println(e.getMessage());
//        }
//        catch(ValidationException e){
//            System.out.println(e.getMessage());
//        }

        //String users_file_name = "data/users.txt";
        Validator<User> validatorUser  = new UserValidator();
        UserDBRepository repoDbUser = new UserDBRepository(
                "social_network","users","postgres","postgres",validatorUser);
        //UserRepository repoUser = new UserRepository(validatorUser,users_file_name);
        UserService userService = new UserService(repoDbUser);

        //String frFileName = "data/friendships.csv";
        Validator<Friendship> friendshipValidator = new FriendshipValidator();
        FriendshipDBRepository repoDbFr = new FriendshipDBRepository(
                "social_network","friendships","postgres","postgres",friendshipValidator
        );
        //FriendshipRepo repoFr = new FriendshipRepo(friendshipValidator,frFileName);
        //FriendshipService serviceFr = new FriendshipService(repoFr);
        FriendshipService serviceFr = new FriendshipService(repoDbFr);


        Console ui = new Console(userService,serviceFr);
        ui.run();
    }
};