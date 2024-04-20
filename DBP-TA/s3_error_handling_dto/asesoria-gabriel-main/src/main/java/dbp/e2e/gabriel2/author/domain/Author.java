package dbp.e2e.gabriel2.author.domain;

import jakarta.persistence.*;
import jakarta.validation.constraints.Max;
import jakarta.validation.constraints.Min;
import lombok.*;

import java.util.Date;
import java.util.Set;

import dbp.e2e.gabriel2.post.domain.Post;

@Entity
@Setter
@Getter
@NoArgsConstructor
@AllArgsConstructor
public class Author {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    private String firstname;

    private String lastname;

    private String email;
    private Date author_birth;
    @OneToMany(mappedBy = "author", fetch = FetchType.LAZY)
    private Set<Post> posts;
}
