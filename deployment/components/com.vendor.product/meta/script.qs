function Component()
{
	
}

Component.prototype.createOperations = function()
{
    component.createOperations();

    component.addOperation("CreateShortcut", "@TargetDir@/Password-creator.exe", "@StartMenuDir@/Password-creator.lnk", "workingDirectory=@TargetDir@");
    
    const documentsFolder = "@HomeDir@/Documents/Password-creator";
    const alphabetsFolder = "@TargetDir@/Password-creator";
    
	component.addOperation("Mkdir", documentsFolder);
    component.addOperation("CopyDirectory", alphabetsFolder, documentsFolder);
}