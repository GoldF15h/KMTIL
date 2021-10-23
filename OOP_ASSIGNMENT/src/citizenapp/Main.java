
package citizenapp;

import javafx.application.Application;
import javafx.stage.Stage;
import database.UserkeyList;


public class Main extends Application {
	
	private static final String PATH = "src/database/keylist"; 
	public static void main(String[] args) throws Exception {
		if (!true) {
                    UserkeyList ukl = new UserkeyList(PATH);			
                    ukl.Login("admin", "admin");
                    ukl.WriteKeyList(PATH);
                    System.out.println("KeyListHaveBeenSaved");
                    System.exit(0);
		}
		else launch(args);
	}
	@Override
	public void start(Stage stage) throws Exception {
		FirstPage p1 = new FirstPage();
		p1.start(stage);
	}
}
