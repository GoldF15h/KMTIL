
package citizenapp;

import citizenapp.Module.CompleteHeader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.ColorPicker;
import javafx.scene.control.Control;
import javafx.scene.control.Label;
import javafx.scene.effect.DropShadow;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;
import javafx.scene.text.Font;
import javafx.scene.text.Text;
import javafx.scene.text.TextAlignment;


public class Setting {
	
	private static Scene scene1;
	private static ColorPicker colorP;
	private final static String css = Setting.class.getResource("style/generalButton.css").toExternalForm();
	public static void display() throws FileNotFoundException, Exception {
		AnchorPane mainPane = new AnchorPane();
		
		//Main Section
		VBox vbox = new VBox(20);
		HBox themeHBox = new HBox();
		Text textInBtn = new Text("Clear History");
		textInBtn.getStyleClass().add("text");
		Button clearLogBtn = new Button();
		clearLogBtn.setGraphic(textInBtn);
		Text t1 = new Text("Change Theme Color : ");
		t1.setFont(Font.font("Neucha", 24));
		t1.setFill(Color.WHITESMOKE);
		colorP = new ColorPicker();
		colorP.setValue(CompleteHeader.getTheme());
		 
		themeHBox.getChildren().addAll(t1, colorP);
		clearLogBtn.setOnAction(e -> {
			Log.getLogList().clear();
			CompleteHeader.getUser1().getLogy().clear();
		});
		vbox.getChildren().addAll(themeHBox, clearLogBtn);
		vbox.getStylesheets().add(css);
		vbox.setAlignment(Pos.CENTER);
		vbox.setLayoutX(230);
		vbox.setLayoutY(250);
		//Primary Background
		Image img1 = new Image(new FileInputStream(CompleteHeader.getPATH_TO_BG1()));
		ImageView mainBg = new ImageView();
		mainBg.setImage(img1);
		mainBg.setFitWidth(800);
		mainBg.setFitHeight(600);
		//Secondary Background
		Image img2 = new Image(new FileInputStream(CompleteHeader.getPATH_TO_BG2()));
		ImageView secondBg = new ImageView();
		secondBg.setFitWidth(600);
		secondBg.setFitHeight(450);
		secondBg.setLayoutX(-75);
		secondBg.setLayoutY(-240);
		Rectangle clip = new Rectangle(secondBg.getFitWidth(), secondBg.getFitHeight() - 75);
		clip.setArcWidth(300);
		clip.setArcHeight(300);
		secondBg.setClip(clip);
		secondBg.setImage(img2);
		secondBg.setEffect(new DropShadow(20, Color.GRAY));
		secondBg.setOpacity(0.8);
		HBox nameHBox = new HBox();
		Label fullNameLabel = new Label(CompleteHeader.getFullName());
		fullNameLabel.setTextFill(Color.WHITE);
		fullNameLabel.setFont(Font.font("MV Boli", 18));
		fullNameLabel.setTextAlignment(TextAlignment.RIGHT);
		nameHBox.setMinWidth(Control.USE_PREF_SIZE);
		nameHBox.setMinHeight(Control.USE_PREF_SIZE);
		nameHBox.setMaxWidth(Control.USE_PREF_SIZE);
		nameHBox.setMaxHeight(Control.USE_PREF_SIZE);
		nameHBox.setPrefWidth(300);
		nameHBox.setPrefHeight(30);
		nameHBox.setLayoutX(465);
		nameHBox.setLayoutY(40);
		nameHBox.getChildren().add(fullNameLabel);
		nameHBox.setAlignment(Pos.CENTER_RIGHT);
		mainPane.getChildren().addAll(mainBg, secondBg, CompleteHeader.getLogo(), CompleteHeader.getNavbar(), CompleteHeader.getTopRight(), nameHBox, vbox);
		
		Scene scene = new Scene(mainPane, 800, 600);
		scene1 = scene;
	}

	public static Scene getScene1() {
		return scene1;
	}

	public static void setScene1(Scene scene1) {
		Setting.scene1 = scene1;
	}
	
	public static void retrieveColor() {
		
	}

	public static Color getColor() {
		return colorP.getValue();
	}
	

	
	
}
