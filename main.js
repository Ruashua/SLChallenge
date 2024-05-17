const { app, BrowserWindow } = require('electron')
const addon = require('./build/Release/hello');

app.whenReady().then(() => {
    console.log('Calling StartObs: ', addon.StartObs())
    console.log('Calling ResetAudio: ', addon.ResetAudio())
    console.log('Calling ResetVideo: ', addon.ResetVideo())

    console.log('Calling OpenModule: ', addon.OpenModule())

    console.log('Calling CreateAudioEncoder: ', addon.CreateAudioEncoder())
    console.log('Calling CreateVideoEncoder: ', addon.CreateVideoEncoder())

    console.log('Calling CreateTwitchService: ', addon.CreateTwitchService())
    console.log('Calling CreateTwitchService: ', addon.CreateRtmpOutput())

    console.log('Calling ShutdownObs: ', addon.ShutdownObs())

    module.exports = addon

    app.quit()
})