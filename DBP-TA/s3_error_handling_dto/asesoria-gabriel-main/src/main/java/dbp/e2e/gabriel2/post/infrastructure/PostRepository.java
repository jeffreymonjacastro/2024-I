package dbp.e2e.gabriel2.post.infrastructure;

import dbp.e2e.gabriel2.post.domain.Post;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface PostRepository extends JpaRepository <Post, Long> {

}
