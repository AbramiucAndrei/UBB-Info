import java.time.LocalDate;
import java.util.Comparator;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class Main {
    public static void main(String[] args) {
        List<Nota> note = getNote(getStudents(), getTeme());
        report1(note, "");
        report2(note, "");
        report3(note,221);
    }


    private static List<Student> getStudents() {
        Student s1 = new Student("andrei", 221);
        s1.setId(2l);
        Student s2 = new Student("dan", 222);
        s2.setId(2l);
        Student s3 = new Student("gigi", 221);
        s3.setId(2l);
        Student s4 = new Student("costel", 222);
        s4.setId(2l);
        return List.of(s1, s2, s3, s4);
    }

    private static List<Tema> getTeme() {
        return List.of(
                new Tema("t1", "desc1"),
                new Tema("t2", "desc2"),
                new Tema("t3", "desc3"),
                new Tema("t4", "desc4")
        );
    }

    private static List<Nota> getNote(List<Student> stud, List<Tema> teme) {
        return List.of(
                new Nota(stud.get(0), teme.get(0), 10d, LocalDate.of(2019, 11, 2), "profesor1"),
                new Nota(stud.get(1), teme.get(0), 9d, LocalDate.of(2019, 11, 2).minusWeeks(1), "profesor1"),
                new Nota(stud.get(1), teme.get(1), 10d, LocalDate.of(2019, 10, 20), "profesor2"),
                new Nota(stud.get(1), teme.get(2), 10d, LocalDate.of(2019, 10, 20), "profesor2"),
                new Nota(stud.get(2), teme.get(1), 7d, LocalDate.of(2019, 10, 28), "profesor1"),
                new Nota(stud.get(2), teme.get(3), 9d, LocalDate.of(2019, 10, 27), "profesor2"),
                new Nota(stud.get(1), teme.get(3), 10d, LocalDate.of(2019, 10, 29), "profesor2")
        );
    }
    private static void report3(List<Nota> note,int grupa){
        note.stream()
                .filter(nota -> nota.getStudent().getGroup()==grupa)
                .collect(
                        Collectors.groupingBy(
                                Nota::getTema,
                                Collectors.counting()
                        )
                )
                .entrySet()
                .stream()
                .sorted(Map.Entry.comparingByValue(Comparator.reverseOrder()))
                .forEach(x -> System.out.println(x.getKey() + " : " + x.getValue()));
    }

    private static void report4(List<Nota> note, int start){
        note.stream()
                .filter(nota -> String.valueOf(nota.getStudent().getGroup()).startsWith(String.valueOf(start)))
                .collect(
                        Collectors.groupingBy(
                            nota -> nota.getStudent().getGroup()
                        )
                )
                .entrySet()
                .stream()
                .sorted(Map.Entry.comparingByValue(Comparator.reverseOrder()))
    }



    /**
     * Lista studentilor al caror nume contin un anumit
     * string (parametru), sortati descrescator in
     * functie de media lor
     * @param note
     * @param s
     */
    private static void report1(List<Nota> note, String s) {
        note.stream()
                .filter(nota -> nota.getStudent().getName().toLowerCase().contains(s.toLowerCase()))
                .collect(
                        Collectors.groupingBy(
                                Nota::getStudent,
                                Collectors.averagingDouble(Nota::getValue)
                        )
                )
                .entrySet()
                .stream()
                .sorted(Map.Entry.comparingByValue(Comparator.reverseOrder()))
                .forEach(e -> System.out.println(e.getKey() + " : " + e.getValue()));
    }

    private static void report1v2(List<Nota> note, String s) {
        note.stream()
                .filter(nota -> nota.getStudent().getName().toLowerCase().contains(s.toLowerCase()))
                .collect(
                        Collectors.groupingBy(Nota::getStudent)
                )
                .entrySet()
                .stream()
                .collect(Collectors.toMap(
                        Map.Entry::getKey,
                        entry -> entry.getValue().stream().mapToDouble(Nota::getValue).average().orElse(0))
                )
                .entrySet()
                .stream()
                .sorted(Map.Entry.comparingByValue(Comparator.reverseOrder()))
//                .sorted((entry1, entry2) -> {
//                    Function<List<Nota>, Double> f = x -> x.stream()
//                            .mapToDouble(Nota::getValue)
//                            .average()
//                            .orElse(0);
//
//                    Double mediaS1 = f.apply(entry1.getValue());
//                    Double mediaS2 = f.apply(entry2.getValue());
//
//                    return mediaS2.compareTo(mediaS1);
//                })
                .forEach(e -> System.out.println(e.getKey() + " : " + e.getValue()));
    }

    private static void report2(List<Nota> note,String s){
        note.stream()
                .filter(nota -> nota.getProfesor().toLowerCase().contains(s.toLowerCase()))
                .collect(
                        Collectors.groupingBy(
                                Nota::getProfesor,
                                Collectors.averagingDouble(Nota::getValue)
                        )
                )
                .entrySet()
                .stream()
                .sorted(Map.Entry.comparingByValue(Comparator.reverseOrder()))
                .forEach( e -> System.out.println(e.getKey() + " : " + e.getValue()));
    }
};