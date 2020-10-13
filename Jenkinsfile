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
          ./tests --gtest_output=xml:results.xml
        '''
      }
    }
  }
  post {
        always {
            xunit (
                thresholds: [ skipped(failureThreshold: '0'), failed(failureThreshold: '0') ],
                tools: [ GoogleTest(pattern: 'build/results.xml') ]
            )
            recordIssues(
                tool: clangtidy(pattern: 'build/*.log'),
                unstableTotalAll: 200,
                failedTotalAll: 220
            )
        }
    }
}
