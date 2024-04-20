package dbp.e2e.gabriel2.author.domain;

import dbp.e2e.gabriel2.author.exception.AuthorNotFoundException;
import dbp.e2e.gabriel2.author.infrastructure.AuthorRepository;
import dbp.e2e.gabriel2.post.domain.Post;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.Set;

@Service
public class AuthorService {

    @Autowired
    private AuthorRepository authorRepository;

    public List<Author> getAll() {
        List<Author> authors = authorRepository.findAll();
        if (authors.isEmpty()) {
            throw new AuthorNotFoundException("No authors found");
        }
        return authors;
    }

    public Author getAuthorById(Long id){
       return authorRepository.findById(id).orElseThrow(() ->
               new AuthorNotFoundException("Author not found with id " + id));
    }

    public Author createAuthor(Author newauthor){
        Author author1 = new Author();
        author1.setFirstname(newauthor.getFirstname());
        author1.setLastname(newauthor.getLastname());
        author1.setEmail(newauthor.getEmail());
        author1.setAuthor_birth(newauthor.getAuthor_birth());
        authorRepository.save(author1);

        return author1;
    }

    public Author updateAuthor(Long id, Author author){
        Author author1 = authorRepository.findById(id)
                .orElseThrow(() -> new AuthorNotFoundException("Author not found with id " + id));
        author1.setFirstname(author.getFirstname());
        author1.setLastname(author.getLastname());
        author1.setEmail(author.getEmail());
        author1.setAuthor_birth(author.getAuthor_birth());
        authorRepository.save(author1);
        return author1;
    }

    public void deleteAuthor(Long id){
        Author author = authorRepository.findById(id)
                .orElseThrow(() -> new AuthorNotFoundException("Author not found with id " + id));
        authorRepository.delete(author);
    }

    public Set<Post> getPostsByAuthor(Long id){
        Author author = authorRepository.findById(id)
                .orElseThrow(() -> new AuthorNotFoundException("Author not found with id " + id));
        return author.getPosts();
    }
}
