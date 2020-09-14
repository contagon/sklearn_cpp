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
          chmod +x tests
          ./tests
        '''
      }
    }
    post {
        always {
            junit 'results.xml'
        }
    }
  }
}
