pipeline {
  agent { dockerfile true }
  stages {
    stage('Build') {
      steps {
        sh '''
          cd data
          python save_data.py
          cd ..
          mkdir build && cd build
          cmake ..
          make
        '''
      }
    }
    stage('Test') {
      steps {
        sh '''
          cd build
          valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --xml=yes --xml-file=valgrind.xml ./tests --gtest_output=xml:results.xml
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
            publishValgrind (
               failBuildOnInvalidReports: false,
               failBuildOnMissingReports: false,
               failThresholdDefinitelyLost: '',
               failThresholdInvalidReadWrite: '',
               failThresholdTotal: '',
               pattern: '*.memcheck',
               publishResultsForAbortedBuilds: false,
               publishResultsForFailedBuilds: false,
               sourceSubstitutionPaths: '',
               unstableThresholdDefinitelyLost: '',
               unstableThresholdInvalidReadWrite: '',
               unstableThresholdTotal: ''
           )
        }
    }
}
