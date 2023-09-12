function getIcon(iconname, filled = false) {
    if (iconname === "") return iconname
    if (iconname.startsWith("qrc:/")) return iconname

    let iconpath = "qrc:/images/"
    iconpath += iconname
    if (filled) iconpath += "-fill"
    iconpath += ".svg"
    return iconpath
}
