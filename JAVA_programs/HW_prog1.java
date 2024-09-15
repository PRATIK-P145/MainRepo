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

    public void setColor(String col){
        color = col;
    }

    public void setWeight(double wet){
        totalweight = totalweight-weight+wet;
        weight = wet;
    }

    public String getColor() {
      return color;
   }
  
   public double getWeight() {
      return weight;
   }

    public  void delweight(){
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
    /**
     * @param args
     */
    public static void main(String[] args){

        Bag[] ball = new Bag[10];

        ball[0] = new Bag();
        ball[1] = new Bag("Blue");
        ball[2] = new Bag(45);
        ball[3] = new Bag("White",55);
        ball[4] = new Bag("Black",99);
        

        Scanner sc = new Scanner(System.in);
        int ch,op ;
        do{
            System.out.print("\n[ Press ENTER to Continue ]");sc.nextLine();
            System.out.println("\n==============================================================================");
            System.out.println("   Choose Action to Perform : \n\t1. Add Ball \n\t2. Total Weight \n\t3. Display List of Balls \n\t4. Delete a Ball \n\t5. Search a Ball \n\t6. Update Ball \n\t7. Exit");
            System.out.println("==============================================================================\n");
            System.out.println("Count : "+Bag.count);
            System.out.print("Enter your choice : ");
            ch = sc.nextInt();
            
            switch(ch){
                case 1 :
                do{
                    System.out.print("[ Press ENTER to Continue ]");sc.nextLine();
                    if(Bag.count == 10){
                        System.out.println("\n=== [[[[[[[[[[[ Bag is FULL ]]]]]]]]]]] ===\n");
                        break;
                    }

                    System.out.println("\n==============================================================================");
                    System.out.println("   Choose a method to add Ball {MAX capacity-10} : \n\t1. Color = default(Red), Weight = default(10) \n\t2. Color = custom , Weight = 20 \n\t3. Color = Blue   , Weight = custom \n\t4. Color = custom , Weight = custom \n\t5. Exit ");
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
                          System.out.print(">> Enter Weight :");
                          double w = sc.nextDouble();

                           ball[Bag.count] = new Bag(w); // here color = blue
                           System.out.println("\n>>> new Ball is added ");
                           System.out.println(">>> Total Balls : "+Bag.count);
                          break;

                        case 4 :
                          System.out.print(">> Enter Color : ");
                          String colr = sc.nextLine();

                          System.out.print(">> Enter Weight :");
                          double wt = sc.nextDouble();

                           ball[Bag.count] = new Bag(colr,wt);
                          System.out.println("\n>>> new Ball is added ");
                          System.out.println(">>> Total Balls : "+Bag.count);
                          break;

                        case 5 : op = 5;
                          break;

                        default : System.out.println("Please Enter a valid choice !");
                         sc.nextLine();
                    }
                       
                }while(op!=5);
                break;

                case 2 : Bag.calcweight();
                  sc.nextLine();
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
                   sc.nextLine();
                   break;

                case 4 : 
                     System.out.print(">> Enter Index to delete (1 to " + Bag.count + "): ");
                     int idx = sc.nextInt();
                     sc.nextLine();

                     ball[idx-1].delweight();
                     Bag.count--;
                     for(int k=(idx-1); k<Bag.count; k++){
                        ball[k] = ball[k+1];
                     }
                     //System.out.println("Count : "+Bag.count);
                     ball[(Bag.count)] = null;
                     System.out.println("\n===== Item Deleted Successfully ! =====");
                     break;

                 case 5 : 
                   int search_choice;
                   do{
                      System.out.print("[ Press ENTER to Continue ]");sc.nextLine();
                      System.out.println("\n==============================================================================");
                      System.out.println("    1. Search by Color        2. Search by Weight\n    3. Search by Index        4. Exit");
                      System.out.println("==============================================================================\n");
                      System.out.print("Enter your choice : ");
                      search_choice = sc.nextInt();
                      sc.nextLine();

                      switch(search_choice){
                         case 1 :
                           System.out.print("Enter Color to be Searched : ");
                           String srch_colr = sc.nextLine();
                           System.out.println("\n====================================");
                           for(int k=0; k<Bag.count; k++){
                              if(ball[k].getColor().equalsIgnoreCase(srch_colr)){
                                System.out.print(" "+(k+1));
                                 ball[k].display();
                              }
                           }
                           System.out.println("====================================\n");
                           break;

                         case 2 :
                           System.out.print("Enter Weight to be Searched : ");
                           double srch_wt = sc.nextDouble();
                           sc.nextLine();
                           System.out.println("\n====================================");
                           for(int i=0; i<Bag.count; i++){
                              if(ball[i].getWeight() == srch_wt){
                                 System.out.print(" "+(i+1));
                                  ball[i].display();
                              }
                           }
                           System.out.println("====================================\n");
                           break;

                         case 3 :
                           System.out.print("Enter Index to be Searched : ");
                           int srch_idx = sc.nextInt();
                           sc.nextLine();
                           System.out.println("\n====================================");
                           System.out.print(" "+(srch_idx));
                           ball[--srch_idx].display();
                           System.out.println("====================================");
                           break;
                        
                         case 4 : break;
                           
                         default : System.out.println("Please enter a Valid Choice !");
                      }
                   }while(search_choice != 4);
                      
                      break;


                 case 6 :
                      System.out.print(">> Enter Index to Update (1-"+Bag.count+") :");
                      int idx1 = sc.nextInt();
                      sc.nextLine();
                      System.out.println("\n==============================================================================");
                      System.out.println("What do you want to Update?\n      1. Color    2. Weight    3. Both");
                      System.out.println("==============================================================================\n");
                      System.out.print("Enter choice : ");
                      int updt_choice = sc.nextInt();
                      sc.nextLine();

                      if(updt_choice == 1 || updt_choice == 3){
                         System.out.print(">> Enter Color :");
                         String colr = sc.nextLine();
                         ball[idx1-1].setColor(colr); 
                      }
                      if(updt_choice == 2 || updt_choice == 3){
                         System.out.print(">> Enter Weight :");
                         double wt = sc.nextDouble();
                         sc.nextLine();
                         ball[idx1-1].setWeight(wt);
                      }

                      System.out.println("\n===== Updated Successfully ! =====");
                      break;

                 case 7 : 
                      break;
                default : System.out.println("Please Enter a valid choice !");  
            }
        }while(ch!=7 );   

     sc.close();
    }      
}