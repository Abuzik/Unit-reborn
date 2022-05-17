extern crate hex;
#[path = "../../transaction/src/lib.rs"]
pub mod transaction;

#[cfg(test)]
mod tests {
    #[test]
    fn it_works() {
        let result = 2 + 2;
        assert_eq!(result, 4);
    }
}


pub mod blockimplementation {
    use sha3::{Digest, Sha3_384};
    use std::time::SystemTime;
    pub use crate::transaction::transaction::Transaction;

    pub struct Block{
        pub date: u128,
        pub index: u64,
        pub hash: String,
        pub tx: Vec<String>,
        pub previous: String
    }

    impl Block{ 
        pub fn new(index: u64, tx: &mut Vec<String>, previous: String) -> Block { 
            Block {
                date: SystemTime::now().duration_since(SystemTime::UNIX_EPOCH).ok().unwrap().as_millis(),
                index: index,
                hash: Block::generate_hash(tx),
                tx: tx.to_vec(),
                previous: previous
            }
        }

        pub fn generate_hash(txs: &mut Vec<String>) -> String {
            let mut hash: String = String::from("");
            for tx in txs { 
                hash = format!("{}{}", &hash, tx);
            }
            let mut hasher = Sha3_384::new();
            hasher.update(hash.as_bytes());
            hex::encode(hasher.finalize())
        }
    }
}