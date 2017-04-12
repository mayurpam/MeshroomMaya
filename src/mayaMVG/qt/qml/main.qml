import QtQuick 1.1
import QtDesktop 0.1

Rectangle {
    color: "#444"
    // Needed to detect top focus changed
    TopFocusHandler {
        anchors.fill: parent
    }

    ColumnLayout
    {
        anchors.fill: parent
        ContextBar {
            id: contextBar
            implicitHeight: 35
            implicitWidth: parent.width
            project: _project
            settingsVisibility: (_project.projectDirectory === "")
        }
        ProjectSettings {
            id: settings
            implicitWidth: parent.width
            Layout.minimumHeight: childrenRect.height
            Layout.maximumHeight: childrenRect.height
            Layout.verticalSizePolicy: Layout.Expanding
            isOpen: contextBar.settingsVisibility
            project: _project
            sliderMinValue: 90
            sliderMaxValue: 180
            onSettingProjectLoaded: contextBar.settingsVisibility = false
            thumbSize: sliderMinValue
        }

        MVGPanel {
            id: componentList
            implicitWidth: parent.width
            Layout.verticalSizePolicy: Layout.Expanding
            thumbSize: settings.thumbSize
            project: _project
            mode: contextBar.mode
        }
    }

    Keys.onPressed: componentList.keyPressed(event.key)
}
