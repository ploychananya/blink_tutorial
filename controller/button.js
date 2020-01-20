
module.exports = async (request, response) => {
    const parameters = request.body
    console.log("Push button!")
    if(parameters.data!== undefined){
        console.log("Data: \t\t"+parameters.data)
    }
    response.send("ok") 
}