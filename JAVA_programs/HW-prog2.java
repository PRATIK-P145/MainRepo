import java.util.Scanner;
class Bag{
    private
      String color;
      double weight;

    private static double totalweight = 0.0;
    static int count = 0;

    public Bag(){
        color = "Red";
        weight = 10.0;
        count += 1;
        totalweight += weight;
    }

    public Bag(String c){
        color = c;
        weight = 20; 
        count+=1; 
        totalweight += weight;
    }

    public Bag(double w){
        color = "Blue";
        weight = w; 
        count+=1; 
        totalweight += weight;
    }

    public Bag(String c,double w){
        color = c;
        weight = w; 
        count+=1; 
        totalweight += weight;
    }

    public String getColor() {
      return color;
  }
  
  public double getWeight() {
      return weight;
  }

    public  void updtweight(){
        totalweight -= this.weight;
    }
   
    public static void calcweight(){
        System.out.println("\n====================================");
        System.out.println("|   Total weight of Bag : "+totalweight+" kg  | ");
        System.out.println("====================================");
    }

    public void display(){
            System.out.println("\t"+color+"\t  "+weight);
    }
    
}

public class HW_prog1 {
    public static void main(String[] args){

        Bag[] ball = new Bag[10];
        

        Scanner sc = new Scanner(System.in);
        int ch,op ;
        do{
            System.out.println("\n==============================================================================");
            System.out.println("   Choose Action to Perform : \n\t1. Add Ball \n\t2. Total Weight \n\t3. Display List of Balls \n\t4.Delete a Ball \n\t5.Search a Ball \n\t6.Update Ball \n\t7. Exit");
            System.out.println("==============================================================================\n");
            System.out.print("Enter your choice : ");
            ch = sc.nextInt();

            switch(ch){
                case 1 :
                do{

                    if(Bag.count == 10){
                        System.out.println("\n=== [[[[[[[[[[[ Bag is FULL ]]]]]]]]]]] ===\n");
                        break;
                    }

                    System.out.println("\n==============================================================================");
                    System.out.println("   Choose a method to add Ball {MAX capacity-10} : \n\t1. Color = default(Red), Weight = default(10) \n\t2. Color = custom , Weight = 20 \n\t3. Color = Blue   , Weight = custom \n\t4. Color = custom , Weight = custom \n\t5.Exit ");
                    System.out.println("==============================================================================\n");
                    System.out.print("Enter your choice : ");
                    op = sc.nextInt();
                    sc.nextLine();
                    
                    switch(op){
                        case 1 : 
                           ball[Bag.count] = new Bag();
                           System.out.println("\n>>> new Ball is added ");
                           System.out.println(">>> Total Balls : "+Bag.count);
                         
                          break;

                        case 2 :
                          System.out.print("Enter Color : ");
                          String c = sc.nextLine();

                           ball[Bag.count] = new Bag(c); // here weight = 20
                           System.out.println("\n>>> new Ball is added ");
                           System.out.println(">>> Total Balls : "+Bag.count);
                          
                          break;

                        case 3 :
                          System.out.print("Enter Weight :");
                          double w = sc.nextDouble();

                           ball[Bag.count] = new Bag(w); // here color = blue
                           System.out.println("\n>>> new Ball is added ");
                           System.out.println(">>> Total Balls : "+Bag.count);
                          
                          break;

                        case 4 :
                          System.out.print("Enter Color : ");
                          String colr = sc.nextLine();

                          System.out.print("Enter Weight :");
                          double wt = sc.nextDouble();

                           ball[Bag.count] = new Bag(colr,wt);
                          System.out.println("\n>>> new Ball is added ");
                          System.out.println(">>> Total Balls : "+Bag.count);
                         
                          break;

                        case 5 : op = 5;
                          break;

                        default : System.out.println("Please Enter a valid choice !");
                    }
                       
                }while(op!=5);
                break;

                case 2 : Bag.calcweight();
                  break;

                case 3 : 
                   System.out.println("\n====================================");
                   System.out.println(" Idx\tColor\t  Weight");
                   System.out.println("====================================");
                   for(int j=0; j<Bag.count; j++){
                       System.out.print(" "+(j+1));
                       ball[j].display();
                   }
                   System.out.println("====================================");
                   break;
                
                case 7 : ch = 4;
                  break;

                  case 4 : 
                  System.out.print("Enter Index to delete (1 to " + Bag.count + "): ");
                  int idx = sc.nextInt(); 
                  
                  idx--; 
              
                  ball[idx].updtweight();
              
                  for(int k = idx; k < Bag.count - 1; k++){
                      ball[k] = ball[k + 1];
                  }
                  
                  ball[Bag.count - 1] = null;
              
                  Bag.count -= 1;
              
                  System.out.println("Bag at index " + (idx + 1) + " has been removed.");
                  break;

                 case 5 :
                 System.out.print("Enter Ball to search : ");
                 String col = sc.nextLine();

                 for(int j=0; j<Bag.count ; j++){
                     if(ball[j].getColor() == col){
                         ball[j].display();
                         System.out.println();
                     }
                 }
                default : System.out.println("Please Enter a valid choice !");
                
            }

        }while(ch!=4 );

        

     sc.close();
    }      
}
