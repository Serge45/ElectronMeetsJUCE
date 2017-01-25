const electron = require('electron');
const {app} = electron;
var {BrowserWindow} = electron;

let mainWindow;

function createWindow () {
  mainWindow = new BrowserWindow({width: 1024, height: 768});

  mainWindow.loadURL(`file://${__dirname}/index.html`);
  mainWindow.webContents.openDevTools();

  mainWindow.on('closed', () => {
    mainWindow = null;
  });
}

app.on('ready', createWindow);

app.on('window-all-closed', () => {
  if (process.platform !== 'darwin') {
    app.quit();
  }
})

app.on('activate', () => {
  if (mainWindow === null) {
    createWindow();
  }
})