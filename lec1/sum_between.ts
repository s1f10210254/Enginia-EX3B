const sum_between = (x: number, y:number)=>{
    let result = 0
    for (let i = x; i <= y; i++){
        result += i;
    }
    return result
}

console.log(sum_between(1,3))