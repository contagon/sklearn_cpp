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
  }
  post {
        always {
            junit 'build/results.xml'
        }
    }
}
