const path = require('path');
const cookieParser = require('cookie-parser');
const logger = require('morgan');
const express = require('express');
const app = express();
const bodyParser = require('body-parser')
const {catchAsyncErrors} = require('./utils/catchAsyncErrors')
const router  =  express.Router()
const routeConfig = require('./config/routes')
const cors = require('cors')

app.use(cors())

app.use(bodyParser.urlencoded({
  extended: false
}));
app.use(bodyParser.json());

app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));


// generating API route
Object.keys(routeConfig).forEach(  (key, index) => {
  routeConfig[key].forEach((route) => {
    const {methods ,path ,controller} = route    
    router[methods.toLowerCase()](`/${key}${path}`, catchAsyncErrors(controller))
  })
})
app.use(express.static('public'));
app.use('/api', router) 


console.log('START LISTEN')

app.use(logger('dev'));

app.listen(8080 , ()=>{
  startAt = new Date()
  console.log(startAt)
  console.log('Blink Tutorial LISTENNING ON PORT ',   8080)
})


module.exports = app;
