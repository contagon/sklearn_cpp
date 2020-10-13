pipeline {
  agent { dockerfile true }
  stages {
    stage('build') {
      steps {
        sh '''
          cd data
          python3 save_data.py
          cd ..
          mkdir build && cd build
          cmake ..
          make 2> clangtidy.log
        '''
      }
    }
    stage('test') {
      steps {
        sh '''
          cd build
          chmod +x tests
          ./tests
        '''
      }
    }
  }
  post {
        always {
            recordIssues(
                tool: clangtidy(pattern: 'build/*.log'),
                unstableTotalAll: 200,
                failedTotalAll: 220
            )
        }
    }
}
