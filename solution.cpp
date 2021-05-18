 typedef struct {
  int S = 0;	
  void p();// wait
  void v();//signal
} s;//semaphore
 
int counter, r1counter=0, r2counter=0, r3counter=0, wrt1counter=0, wrt2counter=0;// shared 

bool Test_and_set(bool *target){
 	bool rv= *target;// old value,  is it true or false?
	*target = true; // new value set to true
	 return rv; // return original value, returne if the flag was initially true or false
} 

bool lock = true;
   
void p(s){//wait
	while(true){
	  	while (Test_and_set(&lock)){
               ; /* do nothing */
               lock=false;
               s--;
 	   }      	
  	}       
}
   
void v(s){//signal
	 
   	   while(Test_and_set(&lock))//check the door...
           ; /* if true do nothing-*/
        lock= true
        s++;
}      
//(Reader 1 function)
int r1(){
        switch (r1counter){
	          case 0: while (true){
   	               p(s);//check the door, if locked do nothing and come back
   	                lock = false;
   	                // entering the critical section and lock the door
   	            cout<<"I am the reader."<<endl; 
   	                v(s)// leave the critical section and unlock the door
                }	   
	r1counter++ ;  	
	        break;
          
}
//(Writer 1 function)
int wrt(){
        switch (wrt1counter){
	          case 0: while (true)
		      p(s);  
                      // here the writer is checking if anyone is in the critical section
// if not it enters the critical section and says..
		      cout<<"I am writing in the CS, there is no one else here "<<endl;
              v(s);// here, once it leaves the critical section it should "unlock" the door so another reader or writer can enter the critical section
	        }
   wrt1counter++
} 


int main() {

cout<<"Reader Writer problem"<<endl;

	while (true){
		for (int i = 0; i<5000000;i++){
			
    		int coin = rand()%5;
    		
		       switch (coin){
	         		case 0: r1();
	        			   break;
	        	//	case 1: r2();
	        	//		   break;
	        	//	case 2: r3();
	          	//			break;
	        	//	case 3: wrt1();
	           	//			break;  
            	      //	case 3: wrt2();
	           	//			break;  
			   }       
	    }
          
   }  
system ("pause");
return 0;
}
