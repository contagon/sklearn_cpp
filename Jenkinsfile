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
        sh 'make test-cpp OUTPUT=cpp_test.xml'
      }
    }
    stage('Format Test'){
      steps {
        sh 'make test-format-python OUTPUT=format_python.log'
        sh 'make test-format-cpp OUTPUT=format_cpp.log'
      }
    }
    stage('Memory Check') {
      steps{
        runValgrind (
            childSilentAfterFork: true,
            excludePattern: '',
            generateSuppressions: true,
            ignoreExitCode: true,
            includePattern: 'build/test/**/*',
            outputDirectory: '',
            outputFileEnding: '.memcheck',
            programOptions: '',
            removeOldReports: true,
            suppressionFiles: '',
            tool: [$class: 'ValgrindToolMemcheck',
              leakCheckLevel: 'full',
              showReachable: true,
              trackOrigins: true,
              undefinedValueErrors: true],
            traceChildren: true,
            valgrindExecutable: '',
            valgrindOptions: '',
            workingDirectory: 'build/test/**/'
          )
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
