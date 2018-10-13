---
layout: post
title:  "Setup coveralls with Java projects"
date:   2018-10-13 20:03:00 +0800
categories: jekyll update
---

It feels painful every time configuring CI using coveralls. Here's some hints when working with Java project.

1. Get the plugin and JaCoCo
2. Turn on the repository in Coveralls
3. Set 'repoToken' in travis as environment variable
4. Reference repoToken in pom of your project using '${env.repoToken}'
```
<plugin>
    <groupId>org.eluder.coveralls</groupId>
    <artifactId>coveralls-maven-plugin</artifactId>
    <configuration>
        <repoToken>${env.repoToken}</repoToken>
    </configuration>
    <version>4.3.0</version>
</plugin>
```

5. Add this to your pom if it doesn't have source encoding
```
<properties>
    <project.build.sourceEncoding>UTF-8</project.build.sourceEncoding>
</properties>
```

6. Add this to travis config file
```
after_success:
  - mvn jacoco:report coveralls:report
```


References:
* [maven plugin with instruction](https://github.com/trautonen/coveralls-maven-plugin)
* [an article shows the big picture](https://medium.com/@swhp/save-your-time-and-life-with-continuous-integration-bf755988ca13)

[jekyll-docs]: http://jekyllrb.com/docs/home
[jekyll-gh]:   https://github.com/jekyll/jekyll
[jekyll-talk]: https://talk.jekyllrb.com/
