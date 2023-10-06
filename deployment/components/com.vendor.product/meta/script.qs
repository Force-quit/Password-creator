function Component()
{
    // default constructor
}

Component.prototype.createOperations = function()
{
    component.createOperations();

    if (systemInfo.productType === "windows") {
        component.addOperation("CreateShortcut", "@TargetDir@/Password-creator.exe", "@StartMenuDir@/Password-creator.lnk",
            "workingDirectory=@TargetDir@");
    }
}