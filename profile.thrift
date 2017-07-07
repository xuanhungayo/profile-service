namespace cpp profile

struct UserProfile {
    1: i32 id
    2: string name
    3: i16 age
}

service ProfileService {
    void put(1:i32 id, 2:UserProfile profile),
    UserProfile get(1:i32 id),
    void remove(1:i32 id)
}
