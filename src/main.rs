use colored::*;

pub fn main() {
    let welcome_message = "Welcome to Algorithms paradice!".green();
    std::print!("{}", welcome_message);
    let dinosour = r"
               __ 
              / _) 
     _/\/\/\_/ / 
   _|         / 
 _|  (  | (  | 
/__.-'|_|--|_|  PapaJ"
        .green();
    std::print!("{}", dinosour);
}
