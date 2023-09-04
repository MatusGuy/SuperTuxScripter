function getIcon(iconname, filled = false) {
    let iconpath = "qrc:/images/"
    iconpath += iconname
    if (filled) iconpath += "-fill"
    iconpath += ".svg"
    return iconpath
}
