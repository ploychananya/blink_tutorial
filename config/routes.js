var {BlinkController} = require('../controller')
module.exports = {
    blink:[
        {
            methods: 'POST',
            path: '/',
            controller: BlinkController
        }
    ]
}