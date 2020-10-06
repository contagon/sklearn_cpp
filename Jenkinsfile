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
          ./tests --gtest_output=xml:results.xml
        '''
      }
    }
    stage('Valgrind') {
      runValgrind (
          childSilentAfterFork: true,
          excludePattern: '',
          generateSuppressions: true,
          ignoreExitCode: true,
          includePattern: 'build/tests',
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
          workingDirectory: ''
        )
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
