const axios = require('axios')

module.exports = async (request, response) => {
    const parameters = request.body
    axios.post('http://'+parameters.ip_node_mcu+'/delay/', parameters.delay)
    .catch((error) =>{
        console.log(error);
    })
    axios.post('http://'+parameters.ip_node_mcu+'/led/', parameters.led)
    .catch((error) =>{
        console.log(error);
    })
    response.send(parameters) 
}