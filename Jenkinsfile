pipeline {
  agent { dockerfile true }
  stages {
    stage('Build') {
      steps {
        sh '''
          cd python/data
          python3 save_data.py
          cd ../..
          make
        '''
      }
    }
    stage('Test') {
      steps {
        sh 'make test-python OUTPUT=python_test.xml'
        sh 'make test-cpp OUTPUT=1'
      }
    }
    stage('Memory Check') {
      steps{
        sh 'make test-mem OUTPUT=1'
      }
    }
    stage('Format Test'){
      steps {
        sh 'make test-format-python OUTPUT=format_python.log'
        sh 'make test-format-cpp OUTPUT=format_cpp.log'
      }
    }
  }

  post {
    always {
        // Load python and CPP tests
        junit 'python_test.xml'
        xunit (
          testTimeMargin: '3000',
          thresholdMode: 1,
          thresholds: [
            skipped(failureThreshold: '0'),
            failed(failureThreshold: '0')
          ],
          tools: [CTest(
              pattern: 'pod-build/Testing/**/*.xml',
              deleteOutputFiles: true,
              failIfNotNew: false,
              skipNoTestFiles: true,
              stopProcessingIfError: true
            )]
        )
        // Load formatting errors
        recordIssues(
          tool: pep8(pattern: 'format_python.log'),
          unstableTotalAll: 200,
          failedTotalAll: 220
        )
        recordIssues(
          tool: clangTidy(pattern: 'format_cpp.log'),
          unstableTotalAll: 200,
          failedTotalAll: 220
        )
        // Load valgrind results
        publishValgrind (
            failBuildOnInvalidReports: false,
            failBuildOnMissingReports: false,
            failThresholdDefinitelyLost: '',
            failThresholdInvalidReadWrite: '',
            failThresholdTotal: '',
            pattern: 'pod-build/tests/**/*.memcheck',
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
