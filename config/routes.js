var {BlinkController, ButtonController} = require('../controller')
module.exports = {
    blink:[
        {
            methods: 'POST',
            path: '/',
            controller: BlinkController
        }
    ],
    button:[
        {
            methods: 'POST',
            path: '/',
            controller: ButtonController
        }
    ]
}