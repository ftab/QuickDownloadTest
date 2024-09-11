import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Window

ApplicationWindow {
    visible: true
    flags: Qt.Window | Qt.FramelessWindowHint

    ColumnLayout {
        Button {
            text: "Download File"
            onClicked: Downloader.downloadFile("https://gist.githubusercontent.com/ftab/818fbe5080a18ecb7332c7fe4542eeb3/raw/82a9750622a5a4db4c5250068cf2f6bba117ff51/test.txt");
        }
        Label {
            id: label
            text: "Result"
        }
    }
    Connections {
        target: Downloader
        function onSuccess()
        {
            label.text = Downloader.toString();
        }
        function onError()
        {
            label.text = "Error";
        }
    }
}
