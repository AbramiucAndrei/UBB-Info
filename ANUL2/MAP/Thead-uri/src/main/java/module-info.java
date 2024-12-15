module threaduri.theaduri {
    requires javafx.controls;
    requires javafx.fxml;


    opens threaduri.theaduri to javafx.fxml;
    exports threaduri.theaduri;
}