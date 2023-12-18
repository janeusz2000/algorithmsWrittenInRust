use std::time::Instant;

const PERFORMANCE_REPETETION: u32 = 10000;

#[allow(dead_code)]
pub fn find_indexes_that_makes_sum(vec: &std::vec::Vec<i32>, sum: i32) -> std::vec::Vec<usize> {

    for x1 in 0..vec.len() {
        for x2 in x1..vec.len() {
            if vec[x1] + vec[x2] == sum {
                return [x1, x2].to_vec();
            }
        }
    }
    [0, 0].to_vec() // sum was not found
}

#[test]
fn find_two_sum_test_1() {
    let vec = [2, 7, 11, 15].to_vec();
    let sum: i32 = 9;
    let expected_indeces = [0, 1].to_vec();
    assert_eq!(find_indexes_that_makes_sum(&vec, sum), expected_indeces);
    let start = Instant::now();
    for _ in 1..PERFORMANCE_REPETETION {
        let _ = find_indexes_that_makes_sum(&vec, sum);
    }
    let duration = start.elapsed();
    println!("Time elapsed doing this function is: {:?}", duration);
}

#[test]
fn find_two_sum_test_2() {
    let vec = [2, 7, 11, 15].to_vec();
    let sum: i32 = 26;
    let expected_indeces = [2, 3].to_vec();
    assert_eq!(find_indexes_that_makes_sum(&vec, sum), expected_indeces);
    let start = Instant::now();
    for _ in 1..PERFORMANCE_REPETETION {
        let _ = find_indexes_that_makes_sum(&vec, sum);
    }
    let duration = start.elapsed();
    println!("Time elapsed doing this function is: {:?}", duration);
}

#[test]
fn find_two_sum_test_3() {
    let vec = [2, 7, 11, 15].to_vec();
    let sum: i32 = 17;
    let expected_indeces = [0, 3].to_vec();
    assert_eq!(find_indexes_that_makes_sum(&vec, sum), expected_indeces);
    let start = Instant::now();
    for _ in 1..PERFORMANCE_REPETETION {
        let _ = find_indexes_that_makes_sum(&vec, sum);
    }
    let duration = start.elapsed();
    println!("Time elapsed doing this function is: {:?}", duration);
}


#[test]
fn find_two_sum_test_4() {
    let vec = (1..10001).collect();
    let sum: i32 = 10001;
    let expected_indeces = [0, 9999].to_vec();
    assert_eq!(find_indexes_that_makes_sum(&vec, sum), expected_indeces);
    let start = Instant::now();
    for _ in 1..PERFORMANCE_REPETETION {
        let _ = find_indexes_that_makes_sum(&vec, sum);
    }
    let duration = start.elapsed();
    println!("Time elapsed doing this function is: {:?}", duration);
}
