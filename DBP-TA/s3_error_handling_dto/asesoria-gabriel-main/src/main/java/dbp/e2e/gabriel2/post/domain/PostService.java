package dbp.e2e.gabriel2.post.domain;

import dbp.e2e.gabriel2.post.exception.PostNotFoundException;
import dbp.e2e.gabriel2.post.infrastructure.PostRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class PostService {

    @Autowired
    private PostRepository postRepository;

    public List<Post> getAll(){
        return postRepository.findAll();
    }

    public Post getById(Long id){
        return postRepository.findById(id).orElseThrow(() ->
                new PostNotFoundException("Post with id " + id + " not found"));
    }

    public Post createPost(Post post){
        Post post1 = new Post();
        post1.setTitle(post.getTitle());
        post1.setContent(post.getContent());
        post1.setDate_published(post.getDate_published());
        post1.setAuthor(post1.getAuthor());
        postRepository.save(post1);
        return post1;
    }
}
