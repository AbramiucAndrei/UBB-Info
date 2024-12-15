package ubb.scs.map.UI;

import ubb.scs.map.domain.Friendship;
import ubb.scs.map.domain.Tuple;
import ubb.scs.map.domain.User;
import ubb.scs.map.domain.validators.ValidationException;
import ubb.scs.map.service.FriendshipService;
import ubb.scs.map.service.UserService;
import ubb.scs.map.utils.MultiMap;

import java.sql.SQLException;
import java.util.Collection;
import java.util.Scanner;

import static java.lang.System.console;
import static java.lang.System.exit;

public class Console {
    private UserService userService;
    private FriendshipService friendshipService;

    public  Console(UserService userService, FriendshipService friendshipService){
        this.userService = userService;
        this.friendshipService = friendshipService;
    }


    void showAllUsers(){
        Iterable<User> all = userService.findAll();
        for(User u : all){
            System.out.println(u);
        }
    }
    void showAllFriendships(){
        Iterable<Friendship> all = friendshipService.findAll();
        for(Friendship fr : all)
            System.out.println(fr);
    }
    void searchUser()  {
        Scanner in = new Scanner(System.in);
        try {
            Long id = Long.parseLong(in.nextLine());
            User searched = userService.findOne(id);
            if(searched==null)
                System.out.println("There isn't an user with this ID");
            else
                System.out.println(searched);

        } catch (Exception e) {
            System.out.println(e);
        }
    }
    void addUser(){
        Scanner in = new Scanner(System.in);
        System.out.print("Enter Firstname: ");
        String firstname = in.nextLine();
        System.out.print("Enter Lastname: ");
        String lastname = in.nextLine();
        try {
            if(userService.save(firstname, lastname)==null)
                System.out.println("User saved succesfully!");
            else
                System.out.println("User already exists!");
        }catch (ValidationException e){
            System.out.println(e);
        }
    }

    void deleteUser(){
        Scanner in = new Scanner(System.in);
        System.out.print("Enter id :");
        long id = Long.parseLong(in.nextLine());
        try{
            if(userService.delete(id)==null)
                System.out.println("There doesn't exist an User with this ID!");
            else
                System.out.println("Removed succesfully!");
        } catch (Exception e) {
            System.out.println(e);
        }
    }
    void updateUser(){
        Scanner in = new Scanner(System.in);
        System.out.print("Enter id :");
        long id = Long.parseLong(in.nextLine());
        try{
            String newFirst,newLast;
            System.out.print("Enter new Firstname: ");
            newFirst= in.nextLine();
            System.out.print("Enter new Lastname: ");
            newLast= in.nextLine();

            User updated= userService.updateUser(id,newFirst,newLast);
            if(updated==null)
                System.out.println("User updated succesfully!");
            else
                System.out.println("ID doesn't exist");

        } catch (Exception e) {
            System.out.println(e);
        }
    }

    void addFriendship(){
        try{
            Scanner in = new Scanner(System.in);

            Long ID1,ID2;
            System.out.println("Enter ID1: ");
            ID1= Long.parseLong(in.nextLine());
            System.out.println("Enter ID2: ");
            ID2= Long.parseLong(in.nextLine());

            User u1,u2;
            u1= userService.findOne(ID1);
            u2= userService.findOne(ID2);
            if(u1==null)
                throw new RuntimeException("Haven't found an user with ID " + ID1.toString());
            if(u2==null)
                throw new RuntimeException("Haven't found an user with ID " + ID2.toString());
            if(friendshipService.save(u1,u2)==null) {

                System.out.println("Friendship save succesfully");
            }
            else
                System.out.println("Friendship already exists!");
        } catch (Exception e) {
            System.out.println(e);
        }

    }
    void removeFriendship(){
        try{
            Scanner in = new Scanner(System.in);

            Long ID1,ID2;
            System.out.println("Enter ID1: ");
            ID1= Long.parseLong(in.nextLine());
            System.out.println("Enter ID2: ");
            ID2= Long.parseLong(in.nextLine());

            User u1,u2;
            u1= userService.findOne(ID1);
            u2= userService.findOne(ID2);
            if(u1==null)
                throw new RuntimeException("Haven't found an user with ID " + ID1.toString());
            if(u2==null)
                throw new RuntimeException("Haven't found an user with ID " + ID2.toString());

            Tuple<Long,Long> pair = new Tuple<>(ID1,ID2);
            if(friendshipService.delete(pair)==null)
                System.out.println("There doesn't exist a friendship between the 2 users");
            else
                System.out.println("Friendship deleted successfully");
        } catch (Exception e) {
            System.out.println(e);
        }
    }



    void showHowManyComunities(){

        Iterable<User> allUsers = userService.findAll();
        int numberOfComunities = friendshipService.calculateNumberOfComunities(allUsers);

        System.out.println("There are " + String.valueOf(numberOfComunities) + " comunities");
    }

    void showComunities(){
        Iterable<User> allUsers = userService.findAll();
        MultiMap<Integer,Long> comunities = friendshipService.allComunities(allUsers);

        for(Integer host : comunities.keySet()){
            System.out.print("Comunity " + String.valueOf(host)+ ": ");
            for(Long friendID : comunities.get(host)){
                System.out.print(String.valueOf(friendID)+ " ");
            }
            System.out.println();
        }
    }

    void showMostSociableComunity(){
        Iterable<User> allUsers = userService.findAll();
        MultiMap<Integer,Long> comunities = friendshipService.allComunities(allUsers);

        Collection<Long> mostSociable = friendshipService.mostSociableComunity(comunities);

        System.out.print("The most sociable comunity: ");
        for(Long userID : mostSociable)
            System.out.print(String.valueOf(userID)+ " ");

        System.out.println();
    }
    void showOptions(){
        String o = "";
        o+="1.Show all users\n";
        o+="2.Search user by id\n";
        o+="3.Add new user\n";
        o+="4.Delete user by id\n";
        o+="5.Update user\n\n";
        o+="6.Add friendship\n";
        o+="7.Show all friendships\n";
        o+="8.Remove friendship\n";
        o+="9.Show how many comunities\n";
        o+="10.Show all comunities\n";
        o+="11.Most sociable comunity\n";
        o+="0.Exit\n";
        System.out.println(o);
    }



    public final void run(){
        while(true){
            showOptions();
            int option = 0 ;
            Scanner in = new Scanner(System.in);
            option= in.nextInt();
            switch (option){
                case 0 :{
                    exit(0);
                }
                case 1 :{
                    showAllUsers();
                    break;
                }
                case 2 :{
                    searchUser();
                    break;
                }
                case 3:{
                    addUser();
                    break;
                }
                case 4 :{
                    deleteUser();
                    break;
                }
                case 5 :{
                    updateUser();
                    break;
                }
                case 6 :{
                    addFriendship();
                    break;
                }

                case 7 :{
                    showAllFriendships();
                    break;
                }
                case 8 :{
                    removeFriendship();
                    break;
                }
                case 9:{
                    showHowManyComunities();
                    break;
                }
                case 10 : {
                    showComunities();
                    break;
                }
                case 11:{
                    showMostSociableComunity();
                    break;
                }
            }
        }
    }
}
