import java.io.*;
import java.util.*;

class Student {
    int studentId;
    String name;
    int rollNo;
    String studentClass;
    double marks;
    String address;

    // Constructor
    public Student(int studentId, String name, int rollNo, String studentClass, double marks, String address) {
        this.studentId = studentId;
        this.name = name;
        this.rollNo = rollNo;
        this.studentClass = studentClass;
        this.marks = marks;
        this.address = address;
    }

    @Override
    public String toString() {
        return studentId + "," + name + "," + rollNo + "," + studentClass + "," + marks + "," + address;
    }

    // Method to display student details
    public void display() {
        System.out.println("ID: " + studentId + ", Name: " + name + ", Roll No: " + rollNo + ", Class: " + studentClass +
                ", Marks: " + marks + ", Address: " + address);
    }
}

public class StudentDatabase {

    static final String FILE_NAME = "student_database.txt";
    static Scanner sc = new Scanner(System.in);

    // Method to add student records to the file
    public static void createDatabase() {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(FILE_NAME, true))) {
            System.out.println("Enter number of students to add:");
            int n = sc.nextInt();
            sc.nextLine();

            for (int i = 0; i < n; i++) {
                System.out.println("Enter Student ID:");
                int id = sc.nextInt();
                sc.nextLine(); // Consume newline

                System.out.println("Enter Name:");
                String name = sc.nextLine();

                System.out.println("Enter Roll No:");
                int rollNo = sc.nextInt();
                sc.nextLine();

                System.out.println("Enter Class:");
                String studentClass = sc.nextLine();

                System.out.println("Enter Marks:");
                double marks = sc.nextDouble();
                sc.nextLine();

                System.out.println("Enter Address:");
                String address = sc.nextLine();

                Student student = new Student(id, name, rollNo, studentClass, marks, address);
                writer.write(student.toString());
                writer.newLine();
            }
            System.out.println("Database created/updated successfully!");
        } catch (IOException e) {
            System.out.println("Error while writing to file: " + e.getMessage());
        }
    }

    // Method to display all records in the file
    public static void displayDatabase() {
        try (BufferedReader reader = new BufferedReader(new FileReader(FILE_NAME))) {
            String line;
            System.out.println("Student Records:");
            while ((line = reader.readLine()) != null) {
                String[] data = line.split(",");
                Student student = new Student(
                        Integer.parseInt(data[0]), data[1], Integer.parseInt(data[2]),
                        data[3], Double.parseDouble(data[4]), data[5]
                );
                student.display();
            }
        } catch (IOException e) {
            System.out.println("Error while reading file: " + e.getMessage());
        }
    }

    // Method to delete a student record by ID
    public static void deleteRecord() {
        System.out.println("Enter Student ID to delete:");
        int deleteId = sc.nextInt();
        File inputFile = new File(FILE_NAME);
        File tempFile = new File("temp.txt");

        try (BufferedReader reader = new BufferedReader(new FileReader(inputFile));
             BufferedWriter writer = new BufferedWriter(new FileWriter(tempFile))) {

            String line;
            boolean found = false;

            while ((line = reader.readLine()) != null) {
                String[] data = line.split(",");
                int id = Integer.parseInt(data[0]);
                if (id == deleteId) {
                    found = true;
                    System.out.println("Record with ID " + deleteId + " deleted.");
                    continue;
                }
                writer.write(line);
                writer.newLine();
            }

            if (!found) {
                System.out.println("Record not found.");
            }

            inputFile.delete();
            tempFile.renameTo(inputFile);

        } catch (IOException e) {
            System.out.println("Error while deleting record: " + e.getMessage());
        }
    }

    // Method to search for a student record by ID
    public static void searchRecord() {
        System.out.println("Enter Student ID to search:");
        int searchId = sc.nextInt();

        try (BufferedReader reader = new BufferedReader(new FileReader(FILE_NAME))) {
            String line;
            boolean found = false;

            while ((line = reader.readLine()) != null) {
                String[] data = line.split(",");
                int id = Integer.parseInt(data[0]);

                if (id == searchId) {
                    Student student = new Student(
                            id, data[1], Integer.parseInt(data[2]),
                            data[3], Double.parseDouble(data[4]), data[5]
                    );
                    student.display();
                    found = true;
                    break;
                }
            }

            if (!found) {
                System.out.println("Record not found.");
            }

        } catch (IOException e) {
            System.out.println("Error while searching record: " + e.getMessage());
        }
    }

    // Method to update a student record
    public static void updateRecord() {
        System.out.println("Enter Student ID to update:");
        int updateId = sc.nextInt();
        File inputFile = new File(FILE_NAME);
        File tempFile = new File("temp.txt");

        try (BufferedReader reader = new BufferedReader(new FileReader(inputFile));
             BufferedWriter writer = new BufferedWriter(new FileWriter(tempFile))) {

            String line;
            boolean found = false;

            while ((line = reader.readLine()) != null) {
                String[] data = line.split(",");
                int id = Integer.parseInt(data[0]);

                if (id == updateId) {
                    System.out.println("Enter updated Name:");
                    sc.nextLine();
                    String name = sc.nextLine();

                    System.out.println("Enter updated Roll No:");
                    int rollNo = sc.nextInt();

                    System.out.println("Enter updated Class:");
                    sc.nextLine();
                    String studentClass = sc.nextLine();

                    System.out.println("Enter updated Marks:");
                    double marks = sc.nextDouble();

                    System.out.println("Enter updated Address:");
                    sc.nextLine();
                    String address = sc.nextLine();

                    Student updatedStudent = new Student(updateId, name, rollNo, studentClass, marks, address);
                    writer.write(updatedStudent.toString());
                    found = true;
                } else {
                    writer.write(line);
                }
                writer.newLine();
            }

            if (!found) {
                System.out.println("Record not found.");
            } else {
                System.out.println("Record updated successfully!");
            }

            inputFile.delete();
            tempFile.renameTo(inputFile);

        } catch (IOException e) {
            System.out.println("Error while updating record: " + e.getMessage());
        }
    }

    public static void main(String[] args) {
        while (true) {
            System.out.println("\n--- Student Database Menu ---");
            System.out.println("1. Create Database");
            System.out.println("2. Display Database");
            System.out.println("3. Delete Record");
            System.out.println("4. Search Record");
            System.out.println("5. Update Record");
            System.out.println("6. Exit");
            System.out.print("Enter your choice: ");
            int choice = sc.nextInt();

            switch (choice) {
                case 1 -> createDatabase();
                case 2 -> displayDatabase();
                case 3 -> deleteRecord();
                case 4 -> searchRecord();
                case 5 -> updateRecord();
                case 6 -> {
                    System.out.println("Exiting program...");
                    System.exit(0);
                }
                default -> System.out.println("Invalid choice! Try again.");
            }
        }
    }
}
