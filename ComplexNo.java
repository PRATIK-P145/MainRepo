// [Q].using JAVA, Design a class ‘Complex ‘with data members for real and imaginary part. 
// Provide default and Parameterized constructors. 
// Write a program to perform arithmetic operations of two complex numbers.
import java.util.Scanner;
class Complex{
    double real = 0.0;
    double img = 0.0;
    double realpart;
    double imgpart;
// Hello
    Complex(){}

    Complex(double r, double i){
        this.real = r;
        this.img = i;
    }

    static Complex add(Complex obj1,Complex obj2){ // by making Methos static,
        double realpart = obj1.real + obj2.real;  // we don't need to create an oject to call the Method
        double imgpart = obj1.img + obj2.img; // we can call this method directly using ClassName

        return new Complex(realpart,imgpart);
    }

    Complex sub(Complex obj){
        realpart = this.real - obj.real;
        imgpart = this.img - obj.img;

        return new Complex(realpart,imgpart);
    }

    static Complex mul(Complex obj1,Complex obj2){
        double realpart = (obj1.real*obj2.real)-(obj1.img*obj2.img);
        double imgpart = (obj1.real*obj2.img)+(obj1.img*obj2.real);

        return new Complex(realpart,imgpart);
    }

    Complex div(Complex obj){
        double denom = (obj.real*obj.real)+(obj.img*obj.img);
         realpart = ((this.real*obj.real)+(this.img*obj.img))/denom;
         imgpart = ((this.img*obj.real)-(this.real*obj.img))/denom;

        return new Complex(realpart,imgpart);
    }

    static void display(Complex obj){
        System.out.println(obj.real+" + "+obj.img+"i");
      }
}
public class ComplexNo {
    public static void main(String[] args){
       Scanner sc = new Scanner(System.in);
       boolean flag=true;
    while(flag) {
       System.out.println("-----Arithmatic Operations on Complex Numbers-----");
       System.out.println(" [1] Addition\n [2] Substraction\n [3] Multiplication\n [4] Division\n [5] Exit");
       System.out.println(); 

       Complex c1 = new Complex();
       Complex c2 = new Complex();

       System.out.println("Enter two Numbers :");
       System.out.print(" realpart : ");
       c1.real = sc.nextDouble();
       System.out.print(" imagpart : ");
       c1.img = sc.nextDouble();
       System.out.print("First No : ");
       Complex.display(c1);

       System.out.print(" realpart : ");
       c2.real = sc.nextDouble();
       System.out.print(" imagpart : ");
       c2.img = sc.nextDouble();
       System.out.print("Second No : ");
       Complex.display(c2);

       System.out.print("Enter Option : ");
       int i = sc.nextInt();
    
     switch(i){
         case 1: Complex c3 = Complex.add(c1,c2); 
                 System.out.println("Addition is : ");
                 Complex.display(c3);
                 break;
         case 2: Complex c4 = c1.sub(c2);
                 System.out.println("Substraction is : ");
                 Complex.display(c4);
                 break;
         case 3: Complex c5 = Complex.mul(c1,c2);
                 System.out.println("Multiplication is : ");
                 Complex.display(c5);
                 break;
         case 4: Complex c6 = c1.div(c2);
                 System.out.println("Division is : ");
                 Complex.display(c6);
                 break;
         case 5: flag =false;
                 break;

         default : System.out.println("Wrong Choice !");
       }
    }
    }
}
