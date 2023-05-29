$AtgFrameworkSource = "$($env:XEDK)\Source\Samples\Common\*"
$AtgFrameworkDestination = "$($PSScriptRoot)\..\deps\AtgFramework"

# Make sure that the Xbox 360 SDK is installed
if (!$env:XEDK) {
    echo "You need to have the Xbox 360 SDK installed!"
    Exit 1
}

# Copy the AtgFramework source code locally
try {
    Copy-Item -Path $AtgFrameworkSource -Destination $AtgFrameworkDestination -Exclude "*.vcxproj*"
} catch {
    echo "Could not copy $($AtgFrameworkSource) into $($AtgFrameworkDestination)!"
    Exit 1
}
